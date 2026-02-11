main()
{

  int count = 0;


  int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


  int first = 1;


  first = (first + 365)%7;


  for(int y = 1901; y <= 2000; y++)
  {

    for(int m = 0; m < 12; m++)
    {

      if(first == 0)
      {
        count++;
      }


      int nextMonth = (m+1)%12;
      first += daysPerMonth[nextMonth];


      if(nextMonth == 1)
      {


        if((y%4 == 0) && ((y%100 != 0) || (y%400 == 0)))
        {
          first--;
        }
      }

      first %= 7;
    }
  }

  cout << count;

  return 0;
}
