RecursiveQueueAndDequeueAllSequenceTest() {
    QString sequence;
    AppendCharacterJob jobA ( QChar( 'a' ), &sequence, this );
    AppendCharacterJob jobB ( QChar( 'b' ), &sequence, this );
    AppendCharacterJob jobC ( QChar( 'c' ), &sequence, this );
    AppendCharacterJob jobD ( QChar( 'd' ), &sequence, this );
    AppendCharacterJob jobE ( QChar( 'e' ), &sequence, this );
    AppendCharacterJob jobF ( QChar( 'f' ), &sequence, this );
    AppendCharacterJob jobG ( QChar( 'g' ), &sequence, this );
    AppendCharacterJob jobH ( QChar( 'h' ), &sequence, this );
    AppendCharacterJob jobI ( QChar( 'i' ), &sequence, this );
    AppendCharacterJob jobJ ( QChar( 'j' ), &sequence, this );
    ThreadWeaver::JobSequence jobSequence1( this );
    jobSequence1.setObjectName( "Sequ_1" );
    jobSequence1.addJob ( &jobA );
    jobSequence1.addJob ( &jobB );
    jobSequence1.addJob ( &jobC );
    ThreadWeaver::JobSequence jobSequence2( this );
    jobSequence2.setObjectName( "Sequ_2" );
    jobSequence2.addJob ( &jobD );
    jobSequence2.addJob ( &jobE );
    jobSequence2.addJob ( &jobF );
    ThreadWeaver::JobSequence jobSequence3( this );
    jobSequence3.setObjectName( "Sequ_3" );
    jobSequence3.addJob ( &jobG );
    jobSequence3.addJob ( &jobH );
    jobSequence3.addJob ( &jobI );
    jobSequence3.addJob ( &jobJ );

    ThreadWeaver::JobSequence jobSequence4( this );
    jobSequence4.setObjectName( "Sequ_4" );
    jobSequence4.addJob ( &jobSequence1 );
    jobSequence4.addJob ( &jobSequence2 );
    jobSequence4.addJob ( &jobSequence3 );

    ThreadWeaver::Weaver::instance()->suspend();

    ThreadWeaver::Weaver::instance()->enqueue ( & jobSequence4 );
    ThreadWeaver::Weaver::instance()->dequeue ();
    bool empty = ThreadWeaver::Weaver::instance()->isEmpty();
    ThreadWeaver::Weaver::instance()->resume();

    ThreadWeaver::Weaver::instance()->finish();

    QVERIFY ( empty == true );
}
