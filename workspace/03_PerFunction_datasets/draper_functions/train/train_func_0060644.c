OGRFeatureShadow_SetField__SWIG_7(OGRFeatureShadow *self,char const *name,int year,int month,int day,int hour,int minute,int second,int tzflag){
      int i = OGR_F_GetFieldIndex(self, name);
      if (i == -1)
	  CPLError(CE_Failure, 1, "No such field: '%s'", name);
      else
	  OGR_F_SetFieldDateTime(self, i, year, month, day,
				 hour, minute, second,
				 tzflag);
  }
