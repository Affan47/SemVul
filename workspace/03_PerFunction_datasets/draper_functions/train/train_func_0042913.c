GC_register(VALUE& obj) {
      if (FIXNUM_P(obj) || SPECIAL_CONST_P(obj) || SYMBOL_P(obj))
        return;
      if (_hash != Qnil) {
        VALUE val = rb_hash_aref(_hash, obj);
        unsigned n = FIXNUM_P(val) ? NUM2UINT(val) : 0;
        ++n;
        rb_hash_aset(_hash, obj, INT2NUM(n));
      }
    }
