moveroamer (int n)
{
   enemy[n].x += enemy[n].speedx;
   enemy[n].y += enemy[n].speedy;
   if (enemy[n].x < SPRITE_SIZE / 2)
   {
      enemy[n].x = SPRITE_SIZE / 2;
      enemy[n].speedx = fabs(enemy[n].speedx);
   }
   if (enemy[n].x > WIDTH - (SPRITE_SIZE / 2))
   {
      enemy[n].x = WIDTH - (SPRITE_SIZE / 2);
      enemy[n].speedx = fabs(enemy[n].speedx) * -1;
   }
   if (enemy[n].y < SPRITE_SIZE / 2)
   {
      enemy[n].y = SPRITE_SIZE / 2;
      enemy[n].speedy = fabs(enemy[n].speedy);
   }
   if (enemy[n].y > HEIGHT - (SPRITE_SIZE / 2))
   {
      enemy[n].y = HEIGHT - (SPRITE_SIZE / 2);
      enemy[n].speedy = fabs(enemy[n].speedy) * -1;
   }

   return;
}
