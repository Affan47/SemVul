checkPdfId()
{
    Poppler::Document *doc;
    doc = Poppler::Document::load("../../../test/unittestcases/A6EmbeddedFiles.pdf");
    QVERIFY( doc );

    const QByteArray referencePermanentId( "00C9D5B6D8FB11D7A902003065D630AA" );
    const QByteArray referenceUpdateId( "39AECAE6D8FB11D7A902003065D630AA" );

    {

    QVERIFY( doc->getPdfId( 0, 0 ) );
    }
    {

    QByteArray permanentId;
    QVERIFY( doc->getPdfId( &permanentId, 0 ) );
    QCOMPARE( permanentId.toUpper(), referencePermanentId );
    }
    {

    QByteArray updateId;
    QVERIFY( doc->getPdfId( 0, &updateId ) );
    QCOMPARE( updateId.toUpper(), referenceUpdateId );
    }
    {

    QByteArray permanentId;
    QByteArray updateId;
    QVERIFY( doc->getPdfId( &permanentId, &updateId ) );
    QCOMPARE( permanentId.toUpper(), referencePermanentId );
    QCOMPARE( updateId.toUpper(), referenceUpdateId );
    }

    delete doc;
}
