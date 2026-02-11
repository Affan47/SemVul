T1_GetFontBBox( int FontID)
{

  BBox outbox= { 0, 0, 0, 0};
  struct ps_obj *obj;


  if (T1_CheckForFontID(FontID)!=1){
    T1_errno=T1ERR_INVALID_FONTID;
    return(outbox);
  }


  obj = &(pFontBase->pFontArray[FontID].pType1Data->fontInfoP[FONTBBOX].value.data.arrayP[0]);
  outbox.llx =
    objPIsInteger(obj) ? obj->data.integer : obj->data.real > 0 ?
    (int) ceil(obj->data.real) : (int) floor(obj->data.real);
  obj = &(pFontBase->pFontArray[FontID].pType1Data->fontInfoP[FONTBBOX].value.data.arrayP[1]);
  outbox.lly =
    objPIsInteger(obj) ? obj->data.integer : obj->data.real > 0 ?
    (int) ceil(obj->data.real) : (int) floor(obj->data.real);
  obj = &(pFontBase->pFontArray[FontID].pType1Data->fontInfoP[FONTBBOX].value.data.arrayP[2]);
  outbox.urx =
    objPIsInteger(obj) ? obj->data.integer : obj->data.real > 0 ?
    (int) ceil(obj->data.real) : (int) floor(obj->data.real);
  obj = &(pFontBase->pFontArray[FontID].pType1Data->fontInfoP[FONTBBOX].value.data.arrayP[3]);
  outbox.ury =
    objPIsInteger(obj) ? obj->data.integer : obj->data.real > 0 ?
    (int) ceil(obj->data.real) : (int) floor(obj->data.real);

  return( outbox);
}
