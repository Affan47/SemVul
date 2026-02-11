Hgetfileversion(int32 file_id, uint32 *majorv, uint32 *minorv,
				uint32 *release, char *string)
{
  CONSTR(FUNC, "Hgetfileversion");
  filerec_t  *file_rec;
  intn      ret_value = SUCCEED;

  HEclear();

  file_rec = HAatom_object(file_id);
  if (BADFREC(file_rec))
    HGOTO_ERROR(DFE_ARGS, FAIL);

  if (majorv != NULL)
      *majorv = file_rec->version.majorv;
  if (minorv != NULL)
      *minorv = file_rec->version.minorv;
  if (release != NULL)
      *release = file_rec->version.release;
  if (string != NULL)
      HIstrncpy(string, file_rec->version.string, LIBVSTR_LEN + 1);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
