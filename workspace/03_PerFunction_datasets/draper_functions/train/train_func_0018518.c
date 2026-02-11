httpBodySet(HttpBody * body, MemBuf * mb)
{
    assert(body);
    assert(memBufIsNull(&body->mb));
    body->mb = *mb;
}
