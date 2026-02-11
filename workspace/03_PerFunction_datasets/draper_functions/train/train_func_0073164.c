readMeshData(int& element_counter, int& node_counter, bool count_only)
{
  Rc rc;

  char* strm_buffer = new char[BUFFER_LEN];
  strstream strm(strm_buffer, BUFFER_LEN, ios::app);

  int keyword_buffer_len = 80;
  char* keyword_buffer = new char[keyword_buffer_len];

  int name_buffer_len = 80;
  char* name_buffer = new char[name_buffer_len];

  UserInterface* gui = theControlCenter->getGui();

  int body_counter = 0;
  int bndr_counter = 0;


  while ( !infile.eof() ) {

    skip_comment_lines();

    bool keyword_found = false;

    if ( next_is_keyword_line() )
      keyword_found = true;


    readFileLine(infile, read_buffer);

    if (!keyword_found)
      continue;

    char* tmp = read_buffer;
    tmp++;

    reset(strm);
    strm << tmp << ends;


    istrstream* istrm = (istrstream*) &strm;

    if ( !readKeyword(istrm, keyword_buffer, 80) )
      keyword_found = false;


    if (!keyword_found)
      continue;


    if ( LibFront::ncEqual(keyword_buffer, (char*)ABQ_ELEMENT) ) {


      if ( !readElementType(istrm, name_buffer, name_buffer_len) ) {
        return ECIF_ERROR;
      }

      int elem_code = findElementCode(name_buffer);

      if (elem_code == (int)NO_INDEX) {

        strstream strm;
        strm << "***ERROR: Unsupported Abaqus element type: ";
        strm << name_buffer << ends;
        gui->showMsg(strm.str());

        return ECIF_ERROR;
      }

      AbaqusElementSet* es = NULL;


      if ( readElementSetName(istrm, name_buffer, name_buffer_len) ) {
        es = findElementSet(name_buffer);
      }

      rc = readElements(es, elem_code, count_only, element_counter);

      if ( rc != ECIF_OK ) return rc;
    }


    else if ( LibFront::ncEqual(keyword_buffer, (char*)ABQ_NODE) ) {

      readNodeSetName(istrm, name_buffer, name_buffer_len);
      readNodes(count_only, node_counter);

      if (!count_only) {
        model->setMeshNodes();


      } else {
        modelDimension = findMeshModelDimension();
      }
    }


    else if ( LibFront::ncEqual(keyword_buffer, (char*)ABQ_ELSET) ) {
      AbaqusElementSet* es = NULL;

      if ( readElementSetName(istrm, name_buffer, name_buffer_len) ) {
        es = findElementSet(name_buffer);
      }

      readElementSet(es, body_counter, bndr_counter, count_only);
    }


    else if ( LibFront::ncEqual(keyword_buffer, (char*)ABQ_NSET) ) {
      readNodeSetName(istrm, name_buffer, name_buffer_len);
      readNodeSet(name_buffer, count_only);
    }

	}

  delete[] keyword_buffer;
  delete[] name_buffer;
  delete[] strm_buffer;

	return ECIF_OK;
}
