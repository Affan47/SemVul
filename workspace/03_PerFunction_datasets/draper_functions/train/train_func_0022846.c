MagickBitStreamMSBRead(BitStreamReadHandle *bit_stream,
						 const unsigned int requested_bits)
{
  register unsigned int
    remaining_quantum_bits,
    quantum;

  remaining_quantum_bits = requested_bits;
  quantum = 0;

  while (remaining_quantum_bits != 0)
    {
      register unsigned int
	octet_bits;

      octet_bits = remaining_quantum_bits;
      if (octet_bits > bit_stream->bits_remaining)
	octet_bits = bit_stream->bits_remaining;

      remaining_quantum_bits -= octet_bits;
      bit_stream->bits_remaining -= octet_bits;

      quantum = (quantum << octet_bits) |
	((*bit_stream->bytes >> (bit_stream->bits_remaining))
	 & BitAndMasks[octet_bits]);

      if (bit_stream->bits_remaining == 0)
	{
	  bit_stream->bytes++;
	  bit_stream->bits_remaining=8;
	}
    }
  return quantum;
}
