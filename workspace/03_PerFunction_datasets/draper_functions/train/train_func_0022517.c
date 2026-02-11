recieve(char command, string message)
{
  if (my_intermediate)
    if (command=='?')
      {

        send(evaluate(false), false);

      }
    else
      if (command=='!')
        {

        }
      else
        {

          my_intermediate->recieve(command+message);
        }
}
