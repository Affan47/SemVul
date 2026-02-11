get_matches (int *nmatches, char *divstring, unsigned int coordstart, unsigned int coordend,
	     int **leftflanks, int *nleftflanks, int **rightflanks, int *nrightflanks,
	     char *typestring, IIT_T *iit, char *filename) {
  int *matches;
  int typeint;

  if (typestring == NULL) {

    if (*iit == NULL) {
      if ((*iit = IIT_read(filename,NULL,true,READ_ONE,divstring,
			   true,false)) == NULL) {
	fprintf(stderr,"File %s appears to be an invalid IIT file\n",filename);
	exit(9);
      }
    }
    matches = IIT_get(&(*nmatches),*iit,divstring,coordstart,coordend,sortp);
    if (nflanking > 0) {
      IIT_get_flanking(&(*leftflanks),&(*nleftflanks),&(*rightflanks),&(*nrightflanks),*iit,divstring,
		       coordstart,coordend,nflanking,0);
    }

  } else if ((typeint = IIT_typeint(*iit,typestring)) < 0) {
    fprintf(stderr,"No such type as %s.  Ignoring the type.\n",typestring);

    if (*iit == NULL) {
      if ((*iit = IIT_read(filename,NULL,true,READ_ONE,divstring,
			   true,false)) == NULL) {
	fprintf(stderr,"File %s appears to be an invalid IIT file\n",filename);
	exit(9);
      }
    }
    matches = IIT_get(&(*nmatches),*iit,divstring,coordstart,coordend,sortp);
    if (nflanking > 0) {
      IIT_get_flanking(&(*leftflanks),&(*nleftflanks),&(*rightflanks),&(*nrightflanks),*iit,divstring,
		       coordstart,coordend,nflanking,0);
    }

  } else {

    if (*iit == NULL) {
      if ((*iit = IIT_read(filename,NULL,true,READ_ONE,divstring,
			   true,false)) == NULL) {
	fprintf(stderr,"File %s appears to be an invalid IIT file\n",filename);
	exit(9);
      }
    }
    matches = IIT_get_typed(&(*nmatches),*iit,divstring,coordstart,coordend,typeint,sortp);
    if (nflanking > 0) {
      IIT_get_flanking_typed(&(*leftflanks),&(*nleftflanks),&(*rightflanks),&(*nrightflanks),*iit,divstring,
			     coordstart,coordend,nflanking,typeint);
    }
  }

  return matches;
}
