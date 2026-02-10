gameTypeChanged()
{
    stopDemo();

    if ( allowedToStartNewGame() )
    {
        setEasy( options->currentItem() == 0 );
        startNew( gameNumber() );
    }
    else
    {


        options->setCurrentItem( easyRules ? 0 : 1 );
    }
}
