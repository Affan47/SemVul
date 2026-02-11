NumPlates(
			const std::map<size_t, std::vector< std::vector<UInt8> >, std::less<size_t> >& data,
			const std::map<size_t, size_t, std::less<size_t> >& elementsize)
	{
		std::map<size_t, size_t, std::less<size_t> >::const_iterator sizeinfo = elementsize.find( VAR_ANALOGUE_FORCE );
		size_t force_element_size = (sizeinfo != elementsize.end()) ? sizeinfo->second : 0;


		if (force_element_size == 0)
			return 0UL;


		if (force_element_size != 2)
      throw(MotionFileException(MotionFileException::formaterror,"Unexpected element size for force data"));


		size_t num_corners = data.find(VAR_FORCE_PLATE_POSITION)->second.size();
    size_t num_sensor_offsets = data.find(VAR_FORCE_PLATE_CONSTANTS)->second.size();
		size_t num_force_types = data.find(VAR_FORCE_PLATE_FLAGS)->second.size();


    size_t num_plates(0);
    if (num_force_types)
    {
			if (elementsize.find(VAR_FORCE_PLATE_FLAGS)->second != 2)
        throw(MotionFileException(MotionFileException::formaterror,"Unexpected element size for force plate flags"));
      num_plates = num_force_types;
    }
    else if (num_corners)
    {
      if (num_corners % 4 != 0)
        throw(MotionFileException(MotionFileException::formaterror,"Error in force plate corners"));
      num_plates = num_corners / 4;
    }
    else
    {

			size_t num_force = data.find(VAR_ANALOGUE_FORCE)->second.size();
      if (num_force % 8 != 0)
        throw(MotionFileException(MotionFileException::formaterror,"No force plate info was given for non-standard plate"));
      num_plates = num_force / 8;
    }


    if (num_corners && num_corners != (4*num_plates))
      throw(MotionFileException(MotionFileException::formaterror,"4 corners per force plate not present"));
    if (num_sensor_offsets && num_sensor_offsets != num_plates)
      throw(MotionFileException(MotionFileException::formaterror,"3 sensor offsets per force plate not present"));


		return num_plates;
	}
