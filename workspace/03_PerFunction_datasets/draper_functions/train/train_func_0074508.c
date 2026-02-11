IsValid(int vm1, VMType vm2)
{
  bool r = false;
  assert( vm1 >= 0 );


  switch(vm2)
    {
  case VM1:
    r = vm1 == 1;
    break;
  case VM2:
    r = vm1 == 2;
    break;
  case VM3:
    r = vm1 == 3;
    break;
  case VM4:
    r = vm1 == 4;
    break;
  case VM5:
    r = vm1 == 5;
    break;
  case VM6:
    r = vm1 == 6;
    break;
  case VM8:
    r = vm1 == 8;
    break;
  case VM16:
    r = vm1 == 16;
    break;
  case VM24:
    r = vm1 == 24;
    break;
  case VM1_2:
    r = (vm1 == 1 || vm1 == 2);
    break;
  case VM1_3:
    r = (vm1 >= 1 && vm1 <= 3);
    break;
  case VM1_8:
    r = (vm1 >= 1 && vm1 <= 8);
    break;
  case VM1_32:
    r = (vm1 >= 1 && vm1 <= 32);
    break;
  case VM1_99:
    r = (vm1 >= 1 && vm1 <= 99);
    break;
  case VM1_n:
    r = (vm1 >= 1);
    break;
  case VM2_2n:
    r = (vm1 >= 2 && !(vm1%2) );
    break;
  case VM2_n:
    r = (vm1 >= 2);
    break;
  case VM3_3n:
    r = (vm1 >= 3 && !(vm1%3) );
    break;
  case VM3_n:
    r = (vm1 >= 3);
    break;
  default:
    assert(0);
    }
  return r;
}
