MDFPlateID() const throw(MotionFileException)
  {
		UInt8 id(0);
    const std::string& model = Model.Value();
		if (Type.Value() == ForcePlate::TypeKistler)
    {
      if (model == "9821B")
        id = type_Kistler_9821B;
      else if (model == "9826")
        id = type_Kistler_9826;
      else if (model == "9821C_1")
        id = type_Kistler_9821C_1;
      else if (model == "9821C_2")
        id = type_Kistler_9821C_2;
      else if (model == "9827")
        id = type_Kistler_9827;
      else if (model == "9261")
        id = type_Kistler_9261;
      else
        id = type_Kistler_9821B;

    }
		else if (Type.Value() == ForcePlate::TypeAMTI)
    {
      if (model == "BP2416")
        id = type_AMTI_BP2416;
      else if (model == "LG6")
        id = type_AMTI_LG6;
			else if (model == "OR6")
        id=type_AMTI_OR6_7;
      else if (model == "AccuSway")
        id = type_AMTI_AccuSway;
      else if (model == "AccuGait")
				id=type_AMTI_AccuGait;
			else
        id = type_AMTI_BP2416;
    }
		else
		{
			throw (MotionFileException(MotionFileException::notsupported, "unsupported force plate type"));
		}

		return id;
  }
