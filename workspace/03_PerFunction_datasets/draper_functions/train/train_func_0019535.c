dotProduct(const Vector& a, const Vector& b) {
   if (a.dim != b.dim) throw Vector::ArithmeticException();
   double d = 0;
   for (int i = 0; i < a.dim; i++)
      d += a._rep[i] * b._rep[i];
   return d;
}
