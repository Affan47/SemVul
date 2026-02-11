match(char *path)
{
  char *oldtoken = NULL, *token = NULL;
  struct stat inode;
  int i;


  while(1)
  {

    if(token == NULL)
    {

      token = strtok(path, "/");
    }
    else
    {

      token = strtok(NULL, "/");


      if(token == NULL)
      {
        for(i = 0; i < 5; i++)
        {

          if(stat(path, &inode) == 0)
            break;


          switch(i)
          {
            case 0:
            {
              case1(oldtoken);
              break;
            }

            case 1:
            {
              case2(oldtoken);
              break;
            }

            case 2:
            {
              case3(oldtoken);
              break;
            }

            case 3:
            {
              case4(oldtoken);
              break;
            }

            default:
            {

              if(case5(path, oldtoken) < 0)
                return -1;
            }
          }
        }
        break;
      }

      for(i = 0; i < 3; i++)
      {

        if(stat(path, &inode) == 0)
          break;


        switch(i)
        {
          case 0:
          {
            case1(oldtoken);
            break;
          }

          case 1:
          {
            case2(oldtoken);
            break;
          }

          default:
          {

            if(case5(path, oldtoken) < 0)
              return -1;
          }
        }
      }


      oldtoken[strlen(oldtoken)] = '/';
    }


    oldtoken = token;
  }


  return 0;
}
