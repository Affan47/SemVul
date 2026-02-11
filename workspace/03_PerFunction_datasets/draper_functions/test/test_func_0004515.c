out( MifOutputByteStream &os ) {

    os << '\n' << MifOutputByteStream::INDENT << "<ImportObject ";
    os.indent();
    outObjectProperties( os );
    CHECK_PROPERTY( ImportObFileDI );
    CHECK_PROPERTY( BitMapDpi );
    CHECK_PROPERTY( ShapeRect );
    CHECK_PROPERTY( ImportObFixedSize );
    CHECK_PROPERTY( NativeOrigin );
    os.undent();
    os << '\n' << MifOutputByteStream::INDENT << ">";
}
