TrueCurrentItem (KSelectAction *sa)
{
  QAction *curAction = sa->currentAction ();


  foreach (QAction *action, sa->actions ())
  {
    if (action->isChecked ())
    {


       if (action != curAction)
       {

         return sa->actions ().indexOf (action);
       }
    }
  }


  return (curAction && curAction->isChecked ()) ? sa->actions ().indexOf (curAction) : -1;
}
