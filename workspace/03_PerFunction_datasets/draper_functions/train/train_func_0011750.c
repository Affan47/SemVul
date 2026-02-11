amitk_data_set_export_to_file(AmitkDataSet *ds,
				       const AmitkExportMethod method,
				       const int submethod,
				       const gchar * filename,
				       const gchar * studyname,
				       const gboolean resliced,
				       const AmitkPoint voxel_size,
				       const AmitkVolume * bounding_box,
				       AmitkUpdateFunc update_func,
				       gpointer update_data) {

  gboolean successful = FALSE;

  switch (method) {
#ifdef AMIDE_LIBDCMDATA_SUPPORT
  case AMITK_EXPORT_METHOD_DCMTK:
    successful = dcmtk_export(ds, filename, studyname, resliced, voxel_size, bounding_box, update_func, update_data);
    break;
#endif
#ifdef AMIDE_LIBMDC_SUPPORT
  case AMITK_EXPORT_METHOD_LIBMDC:
    successful = libmdc_export(ds, filename, submethod, resliced, voxel_size, bounding_box, update_func, update_data);
    break;
#endif
  case AMITK_EXPORT_METHOD_RAW:
  default:
    successful = export_raw(ds, filename, resliced, voxel_size, bounding_box, update_func, update_data);
    break;
  }


  return successful;
}
