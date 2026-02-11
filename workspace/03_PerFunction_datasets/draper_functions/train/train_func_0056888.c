cattest()
{
#define assert_eq(ofstr, c_str) \
  assert(ofstr == OFString(c_str, sizeof(c_str)/sizeof(char) - 1))

  OFString x = X;
  OFString y = Y;
  OFString z = x + y;
  COUT << "z = x + y = " << z << "\n";
  assert_eq(z, "Helloworld\0How are you?");

  x += y;
  COUT << "x += y; x = " << x << "\n";
  assert_eq(x, "Helloworld\0How are you?");

  y = Y;
  x = X;
  y.insert (0, x);
  COUT << "y.insert (0, x); y = " << y << "\n";
  assert_eq(y, "Helloworld\0How are you?");

  y = Y;
  x = X;
  x = x + y + x;
  COUT << "x = x + y + x; x = " << x << "\n";
  assert_eq(x, "Helloworld\0How are you?Hello");

  y = Y;
  x = X;
  x = y + x + x;
  COUT << "x = y + x + x; x = " << x << "\n";
  assert_eq(x, "world\0How are you?HelloHello");

  x = X;
  y = Y;
  z = x + s + ' ' + y.substr (y.find ('w'), 1) + y.substr (y.find ('w') + 1, y.find('\0') - y.find('w')) + ".";
  COUT << "z = x + s +  + y.substr (y.find (w), 1) + y.substr (y.find (w) + 1, y.find('\\0') - y.find('w')) + . = " << z << "\n";
  assert_eq(z, "Hello, world\0.");
#undef assert_eq
}
