WrappedMainIteration() {
  MainLevel++;
  gtk_main_iteration();
  MainLevel--;
  if ((!MainLevel)&&(QuitPending))
    Global::WrappedMainQuit();
}
