reiniciaContadors(){
    actualitzaPuntuacio(-configuracioJoc->comptadorFigures,
                        -configuracioJoc->comptadorPunts);
    rellotgeLabel->estableixTemps("00:00:00");
}
