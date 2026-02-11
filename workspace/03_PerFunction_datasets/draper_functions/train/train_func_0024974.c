update(const float amount)
{

  floatpoint tempcenter;

  tempcenter.x = center.x + velocity.x * amount;
  tempcenter.y = center.y + velocity.y * amount;


  if (tempcenter.x - getradius() < int(boundary->leftx) ||
      tempcenter.x + getradius() > int(boundary->rightx))
    {
      velocity.x *= -1;
      return;
    }

  if (tempcenter.y - getradius() < int(boundary->topy) ||
      tempcenter.y + getradius() > int(boundary->bottomy))
    {
      velocity.y *= -1;
      return;
    }

  ball * collision;

  collision = iscloseto(tempcenter, getradius(), package);

  if (collision != NULL)
    {
      collide(collision);
      return;
    }

  center = tempcenter;
}
