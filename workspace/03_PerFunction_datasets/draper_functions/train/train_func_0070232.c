param_value(int i)const
{
  switch (MODEL_BUILT_IN_MOS_BASE::param_count() - 1 - i) {
  case 0:  unreachable(); return "";
  case 1:  return _tnom_c.string();
  case 2:  return fc.string();
  case 3:  return pb.string();
  case 4:  return cjo.string();
  case 5:  return mj.string();
  case 6:  return cjsw.string();
  case 7:  return pbsw.string();
  case 8:  return mjsw.string();
  case 9:  return kf.string();
  case 10:  return af.string();
  case 11:  return level.string();
  case 12:  return wmax.string();
  case 13:  return wmin.string();
  case 14:  return lmax.string();
  case 15:  return lmin.string();
  case 16:  return is.string();
  case 17:  return js.string();
  case 18:  return rsh.string();
  case 19:  return rd.string();
  case 20:  return rs.string();
  case 21:  return cbd.string();
  case 22:  return cbs.string();
  case 23:  return cgso.string();
  case 24:  return cgdo.string();
  case 25:  return cgbo.string();
  case 26:  return cmodel.string();
  case 27:  return xl.string();
  case 28:  return xw.string();
  case 29:  return lmlt.string();
  case 30:  return wmlt.string();
  case 31:  return del.string();
  case 32:  return ld.string();
  case 33:  return wd.string();
  default: return "";
  }
}
