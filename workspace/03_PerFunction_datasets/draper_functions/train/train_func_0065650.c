MassiveJobSequenceTest() {
    const int NoOfChars = 1024;
    const char* Alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int SizeOfAlphabet = strlen( Alphabet );
    AppendCharacterAndVerifyJob jobs[NoOfChars];
    ThreadWeaver::JobSequence jobSequence( this );
    QString sequence;
    QString in;

    srand ( 1 );
    in.reserve( NoOfChars );
    sequence.reserve ( NoOfChars );
    for ( int i = 0; i<NoOfChars; ++i ) {
        const int position = static_cast<int> ( SizeOfAlphabet * ( ( 1.0 * rand() ) / RAND_MAX ) );
        Q_ASSERT ( 0 <= position && position < SizeOfAlphabet );
        QChar c( Alphabet[position] );
        in.append ( c );
    }

    for ( int i = 0; i<NoOfChars; ++i ) {
        jobs[i].setValues( in.at(i), &sequence, in );
        jobSequence.addJob ( & ( jobs[i] ) );
    }

    QVERIFY(ThreadWeaver::Weaver::instance()->isIdle());
    ThreadWeaver::Weaver::instance()->enqueue ( &jobSequence );
    ThreadWeaver::Weaver::instance()->finish();
    QVERIFY(ThreadWeaver::Weaver::instance()->isIdle());
    QCOMPARE ( sequence, in );
}
