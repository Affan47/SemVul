getObjTypeByIdx(hsize_t idx, char* type_name) const
{
   H5G_obj_t obj_type = H5Gget_objtype_by_idx(getLocId(), idx);
   switch (obj_type)
   {
	case H5G_LINK: HDstrcpy(type_name, "symbolic link"); break;
	case H5G_GROUP: HDstrcpy(type_name, "group"); break;
	case H5G_DATASET: HDstrcpy(type_name, "dataset"); break;
	case H5G_TYPE: HDstrcpy(type_name, "datatype"); break;
	case H5G_UNKNOWN:
	default:
   	{
	   throwException("getObjTypeByIdx", "H5Gget_objtype_by_idx failed");
	}
   }
   return (obj_type);
}
