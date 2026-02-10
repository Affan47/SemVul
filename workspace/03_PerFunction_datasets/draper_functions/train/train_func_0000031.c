out( MifOutputByteStream &os ) {

    os << '\n' << MifOutputByteStream::INDENT << "<XRef ";
    os.indent();
    CHECK_PROPERTY( XRefName );
    if( setProperties & fXRefSrcText )
        XRefSrcText.escapeSpecialChars();
    CHECK_PROPERTY( XRefSrcText );
    CHECK_PROPERTY( XRefSrcFile );
    os.undent();
    os << '\n' << MifOutputByteStream::INDENT << ">";
    if( setProperties & fXRefText )
        os << '\n' << MifOutputByteStream::INDENT
           << "<String " << XRefText << ">";
    os << '\n' << MifOutputByteStream::INDENT << "<XRefEnd>";
}
