slotViewSetFractalAlgorithm(QAction* action)
{
   const int algorithmID = action->data().toInt();
   if(algorithmID < 1000000) {
      View->changeAlgorithm(algorithmID);
      View->configChanged();
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
   }
}
