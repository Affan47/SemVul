CSFD(bool update)
{
   Update = false;
   ifstream in((Dir+"multwc.txt").c_str());
   ReadVerify(in);
   x = 0; crry = 0;
   char xx;
   int n;
   for (n = 28; n >= 0; n -= 4) { in >> xx; x |= unhex(xx, n); }
   for (n = 28; n >= 0; n -= 4) { in >> xx; crry |= unhex(xx, n); }
   ReadVerify(in);
   in.close();
   Update = update;
}
