ChangeValueMin (int NbArg,long *TabArg)
{
  int i=0;
  char *arg[2];
  int j;

  arg[0] = CalcArg(TabArg,&i);
  i++;
  arg[1] = CalcArg(TabArg,&i);
  j = atoi(arg[0]);

  tabxobj[TabIdObj[j]]->value2 = atoi(arg[1]);

  if (tabxobj[TabIdObj[j]]->value < tabxobj[TabIdObj[j]]->value2)
  {
    tabxobj[TabIdObj[j]]->value = atoi(arg[1]);
    if (tabxobj[TabIdObj[j]]->TypeWidget != SwallowExec)
      XClearWindow(dpy, tabxobj[TabIdObj[j]]->win);
    tabxobj[TabIdObj[j]]->DrawObj(tabxobj[TabIdObj[j]],NULL);
  }
  free(arg[0]);
  free(arg[1]);
}
