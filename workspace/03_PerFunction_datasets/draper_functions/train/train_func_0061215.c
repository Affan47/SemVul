command_print_meta(ParsingByteStream &)
{
  if (! g().file )
    {
      GP<DjVmDir::File> frec = g().doc->get_djvm_dir()->get_shared_anno_file();
      if (frec)
        {
          vprint("print-meta: implicitly selecting shared annotations");
          select_clear();
          select_add(frec);
        }
    }
  if ( g().file )
    {
      GP<ByteStream> out=ByteStream::create("w");
      GP<ByteStream> anno = g().file->get_anno();
      if (! (anno && anno->size())) return;
      GP<IFFByteStream> iff=IFFByteStream::create(anno);
      print_meta(*iff,*out);
    }
}
