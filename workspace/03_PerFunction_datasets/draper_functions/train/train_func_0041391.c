translate_layout()
{

    int total = 0;

    for ( int w = 0; w < 10; ++w ) {
        int i = translate_pile(deal->store[w], W[w], 52);
        Wp[w] = &W[w][i - 1];
        Wlen[w] = i;
        total += i;
    }

    for (int i = 0; i < 4; ++i) {
        O[i] = -1;
        KCard *c = deal->target[i]->topCard();
        if (c) {
            total += 13;
            O[i] = translateSuit( c->suit() );
        }
    }
}
