main(int, const char *argv[])
{
   setlocale(LC_ALL, "");

   RSHMethod Mth;
   Prog = strrchr(argv[0],'/');
   Prog++;
   return Mth.Run();
}
