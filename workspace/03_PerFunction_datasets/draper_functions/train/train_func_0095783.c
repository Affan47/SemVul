uca_ring_buffer_available (UcaRingBuffer *buffer)
{
    g_return_val_if_fail (UCA_IS_RING_BUFFER (buffer), FALSE);
    return buffer->priv->read_index < buffer->priv->write_index;
}
