new_game(struct state *st)
{

  st->ball.x = PONG_W/2;
  st->ball.y = PONG_H/2;
  st->bx = st->m_unit;
  st->by = st->m_unit;


  if (random() & 1) st->by = -st->by;
  st->ball.y += (random() % (PONG_H/6))-(PONG_H/3);

  st->l_paddle.wait = 1;
  st->l_paddle.lock = 0;
  st->r_paddle.wait = 0;
  st->r_paddle.lock = 0;
  st->paddle_rate = st->m_unit-1;
  reset_score(st);

  st->l_paddle.h = PONG_H/4;
  st->r_paddle.h = PONG_H/4;
}
