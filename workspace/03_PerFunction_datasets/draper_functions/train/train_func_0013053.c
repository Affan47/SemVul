tolua_px_ecl_GS_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GS",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const Rect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Rect* clipr = ((const Rect*)  tolua_tousertype(tolua_S,2,0));
  {
   GS* tolua_ret = (GS*)  new GS(*clipr);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
