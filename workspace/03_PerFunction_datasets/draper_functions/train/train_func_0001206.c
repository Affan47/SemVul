onCmdFilter(FXObject*,FXSelector sel,void*){
  if (FXSELID(sel)==ID_FILTER_MODE && filterfield->getText().empty())
    return 1;
  if (FXSELTYPE(sel)==SEL_CHANGED) {
    getApp()->addTimeout(this,ID_FILTER,TIME_MSEC(500));
    return 1;
    }
  if (FXSELTYPE(sel)==SEL_COMMAND){
    getApp()->removeTimeout(this,ID_FILTER);
    }
  if (source->setFilter(filterfield->getText().trim().simplify(),filtermask))
    refresh();
  return 1;
  }
