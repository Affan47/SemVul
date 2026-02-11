operator-(Random& rv)
{
   NegatedRandom* r = new NegatedRandom(rv);
   if (!r) ErrorNoSpace(); return *r;
}
