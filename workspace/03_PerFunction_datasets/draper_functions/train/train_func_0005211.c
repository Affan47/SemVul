OGRFeatureShadow_UnsetField__SWIG_1(OGRFeatureShadow *self,char const *name){
      int i = OGR_F_GetFieldIndex(self, name);
      if (i == -1)
	  CPLError(CE_Failure, 1, "No such field: '%s'", name);
      else
	  OGR_F_UnsetField(self, i);
  }
