tolua_px_ecl_Rect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int xx = ((int)  tolua_tonumber(tolua_S,2,0));
  int yy = ((int)  tolua_tonumber(tolua_S,3,0));
  int ww = ((int)  tolua_tonumber(tolua_S,4,0));
  int hh = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   Rect* tolua_ret = (Rect*)  new Rect(xx,yy,ww,hh);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Rect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
