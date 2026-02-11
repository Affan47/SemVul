ring_supplied(Ring *ring, int count)
{
    ring->supply = ring_increment(ring, ring->supply, count);
    ring->supplytime = ++ring_clock;
}
