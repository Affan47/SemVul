visit(const char* value,orbOptions::Source) throw (orbOptions::BadParam) {

    CORBA::ULong v;
    if (!orbOptions::getULong(value,v) || v < 1) {
      throw orbOptions::BadParam(key(),value,
				 orbOptions::expect_greater_than_zero_ulong_msg);
    }
    orbParameters::maxServerThreadPoolSize = v;
  }
