directoriFiguresPersonals(){
    QDir dirArxiu(QDir::homePath ());
    if (!dirArxiu.exists(DIR_ARXIUS_FIGURES_PERSONALS)){
         dirArxiu.mkdir(DIR_ARXIUS_FIGURES_PERSONALS);
      }
 return QDir::homePath ()+QDir().separator()+DIR_ARXIUS_FIGURES_PERSONALS;
}
