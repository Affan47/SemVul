hurt_thing(int h, int damage, int special)
        {

                if (damage < 1) return(0);
                int num = damage - spr[h].defense;


                if (num < 1) num = 0;

                if (num == 0)
                {
                        if ((rand() % 2)+1 == 1) num = 1;
                }

                spr[h].damage += num;
                return(num);

        }
