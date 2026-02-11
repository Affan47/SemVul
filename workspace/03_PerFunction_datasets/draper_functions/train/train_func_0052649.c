setUsesThreads( bool set, bool ovwrt )
{
  static bool first = true;

  if( first || ovwrt )
  {
#if !(defined(HAVE_THREADS) && HAVE_THREADS)
    if( set )
    {
      std::cerr << "Unfortunately, this installation of VampirTrace was not "
                << "compiled with" << std::endl
                << "Multithreading support." << std::endl;
      exit(1);
    }
#endif

    first = false;
    uses_threads = set;
  }
}
