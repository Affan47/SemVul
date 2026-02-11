gen_number(double float_val, int kind)
{
    switch (kind) {
      case 'x':
	_true.x += float_val;
	float_val = _true.x - _false.x;
	break;
      case 'y':
	_true.y += float_val;
	float_val = _true.y - _false.y;
	break;
      case 'X':
	_true.x = float_val;
	break;
      case 'Y':
	_true.y = float_val;
	break;
    }


    int big_val = (int)floor(float_val * _f_precision + 0.50001);

    gen_rational(big_val, _precision);

    float_val = big_val / _f_precision;
    switch (kind) {
      case 'x':
	_false.x += float_val;
	break;
      case 'y':
	_false.y += float_val;
	break;
      case 'X':
	_false.x = float_val;
	break;
      case 'Y':
	_false.y = float_val;
	break;
    }
}
