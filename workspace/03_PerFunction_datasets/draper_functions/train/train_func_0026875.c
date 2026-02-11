writeTix(FILE *f) {
  HpcModuleInfo *tmpModule;
  unsigned int i, inner_comma, outer_comma;

  outer_comma = 0;

  if (f == 0) {
    return;
  }

  fprintf(f,"Tix [");
  tmpModule = modules;
  for(;tmpModule != 0;tmpModule = tmpModule->next) {
    if (outer_comma) {
      fprintf(f,",");
    } else {
      outer_comma = 1;
    }
    fprintf(f," TixModule \"%s\" %u %u [",
	   tmpModule->modName,
	    (nat)tmpModule->hashNo,
	    (nat)tmpModule->tickCount);
    debugTrace(DEBUG_hpc,"%s: %u (hash=%u)\n",
	       tmpModule->modName,
	       (nat)tmpModule->tickCount,
               (nat)tmpModule->hashNo);

    inner_comma = 0;
    for(i = 0;i < tmpModule->tickCount;i++) {
      if (inner_comma) {
	fprintf(f,",");
      } else {
	inner_comma = 1;
      }

      if (tmpModule->tixArr) {
	fprintf(f,"%" FMT_Word64,tmpModule->tixArr[i]);
      } else {
	fprintf(f,"0");
      }
    }
    fprintf(f,"]");
  }
  fprintf(f,"]\n");

  fclose(f);
}
