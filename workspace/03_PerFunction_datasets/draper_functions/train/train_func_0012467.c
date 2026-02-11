continuaCercaNomFiguraSlot(){
    bool trobat=false;
for(int i=indexFiguraPerCercar;i<=arbreFiguresTreeWidget->topLevelItem(0)->childCount()-1;i++){
    indexFiguraPerCercar=i;
    if (arbreFiguresTreeWidget->topLevelItem(0)->child(i)->text(0).contains(
           nomFiguraPerCercar,Qt::CaseInsensitive)){
       arbreFiguresTreeWidget->setCurrentItem(arbreFiguresTreeWidget->topLevelItem(0)->child(i));
       indexFiguraPerCercar=i+1;
       trobat=true;
       break;
    }
 }

if (!trobat){
    nomFiguraPerCercar.clear();
    indexFiguraPerCercar=0;
    continuaCercaNomFigura->setEnabled(false);
    QMessageBox::information(this, configuracioJoc->tradueixCadena("cerca.nom.figura"),
                    configuracioJoc->tradueixCadena("msg.nomFigura.noTrobada"));
  }
}
