fillNameHashes()
{
    s_digitNames[1] = QLatin1String( "arabicOne" );
    s_digitNames[2] = QLatin1String( "arabicTwo" );
    s_digitNames[3] = QLatin1String( "arabicThree" );
    s_digitNames[4] = QLatin1String( "arabicFour" );
    s_digitNames[5] = QLatin1String( "arabicFive" );
    s_digitNames[6] = QLatin1String( "arabicSix" );
    s_digitNames[7] = QLatin1String( "arabicSeven" );
    s_digitNames[8] = QLatin1String( "arabicEight" );

    s_stateNames[KMinesState::Released].append(QLatin1String( "cell_up" ));
    s_stateNames[KMinesState::Pressed].append(QLatin1String( "cell_down" ));
    s_stateNames[KMinesState::Revealed].append(QLatin1String( "cell_down" ));
    s_stateNames[KMinesState::Questioned].append(QLatin1String( "cell_up" ));
    s_stateNames[KMinesState::Questioned].append(QLatin1String( "question" ));
    s_stateNames[KMinesState::Flagged].append(QLatin1String( "cell_up" ));
    s_stateNames[KMinesState::Flagged].append(QLatin1String( "flag" ));
    s_stateNames[KMinesState::Error].append(QLatin1String( "cell_down" ));
    s_stateNames[KMinesState::Error].append(QLatin1String( "mine" ));
    s_stateNames[KMinesState::Error].append(QLatin1String( "error" ));
    s_stateNames[KMinesState::Hint].append(QLatin1String( "cell_up" ));
    s_stateNames[KMinesState::Hint].append(QLatin1String( "hint" ));
}
