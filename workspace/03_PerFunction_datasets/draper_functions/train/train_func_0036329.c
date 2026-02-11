_dxf_newHwGather(void)
{
  gatherP	ret;
  gatherO	go;

  ENTRY(("_dxf_newGather()"));

  ret = (gatherP)DXAllocateZero(sizeof(gatherT));
  if(!ret)
    goto error;

  ret->lights = _dxf_newList(8, (int(*)(void*))DXDelete);
  if(!ret->lights)
    goto error;

  go = (gatherO)_dxf_newHwObject(HW_CLASS_GATHER,
				(Pointer)ret, _deleteGather);
  if (!go)
    goto error;

  EXIT(("ret = 0x%x", ret));
  return go;

 error:
  if(ret) {
    DXFree(ret);
    ret = NULL;
  }

  EXIT(("ERROR"));
  DXErrorReturn(ERROR_NO_MEMORY,"");
}
