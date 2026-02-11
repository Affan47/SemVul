initPagesPerSheet()
{
    setPagesPerSheet( OnePagePerSheet );
    ui.oneUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nup1.png" ) ) );
    ui.twoUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nup2.png" ) ) );
    ui.fourUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nup4.png" ) ) );
    ui.sixUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nupother.png" ) ) );
    ui.nineUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nupother.png" ) ) );
    ui.sixteenUpRadioButton->setIcon( QIcon( KStandardDirs::locate( "data", "kdeui/pics/kdeprint_nupother.png" ) ) );
}
