value_from_trans(int value, int height) {

   ASSERT(value_is_ok(value));
   ASSERT(height_is_ok(height));

   if (value < -ValueEvalInf) {
      value += height;
   } else if (value > +ValueEvalInf) {
      value -= height;
   }

   ASSERT(value_is_ok(value));

   return value;
}
