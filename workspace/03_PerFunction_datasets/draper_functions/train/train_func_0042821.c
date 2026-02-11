seqReaderSetSetConsumerNextPos(struct seqReaderState *consumer,
                               unsigned long newPos)
{
  gt_assert(consumer && consumer->nextReadPos <= newPos);
  consumer->nextReadPos = newPos;
}
