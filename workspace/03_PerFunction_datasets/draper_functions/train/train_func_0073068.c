choice(void) {
    if (!stable())
      throw SpaceNotStable("Space::choice");
    if (failed() || (b_status == Brancher::cast(&bl))) {


      Brancher* b = Brancher::cast(bl.next());
      while (b != Brancher::cast(&bl)) {
        Brancher* d = b;
        b = Brancher::cast(b->next());
        rfree(d,d->dispose(*this));
      }
      bl.init();
      b_status = b_commit = Brancher::cast(&bl);
      return NULL;
    }


    Brancher* b = Brancher::cast(bl.next());
    while (b != b_status) {
      Brancher* d = b;
      b = Brancher::cast(b->next());
      d->unlink();
      rfree(d,d->dispose(*this));
    }

    b_commit = b_status;
    return b_status->choice(*this);
  }
