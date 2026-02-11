readNofMeshElements(int data_set, int& nof_elements,
                                int& max_element_id, int& max_material_id)
{
  int el_id, material_id, dummy, nof_nodes;
  short el_code;

  char* strm_buffer = new char[BUFFER_LEN];
  strstream strm(strm_buffer, BUFFER_LEN, ios::app);


  readFileLine(infile, read_buffer);
	while (! endofDataset(read_buffer)) {

    reset(strm);
    strm << read_buffer << ends;


	  strm >> el_id;
    if (el_id > max_element_id)
      max_element_id = el_id;


	  strm >> el_code;
    elementCodeCounters[el_code]++;


		if (data_set == DS_ELEMENTS_780) {
		  strm >> dummy >> dummy >> dummy >> material_id >> dummy;
    }
		else if (data_set == DS_ELEMENTS_2412) {
		  strm >> dummy >> material_id >> dummy;
    }

    if ( material_id > max_material_id ) {
      max_material_id = material_id;
    }


    strm >> nof_nodes;


    int count = 0;
    while ( count < nof_nodes ) {

		  readFileLine(infile, read_buffer);

      reset(strm);
		  strm << read_buffer << ends;

      while ( count < nof_nodes && (strm >> dummy) ) {
        count++;
      }
    }

    nof_elements++;

    theControlCenter->update(nof_elements, GUI_UPDATE_INTERVAL);


		readFileLine(infile, read_buffer);
	}

  delete[] strm_buffer;

	return ECIF_OK;
}
