vring_kick(unsigned int ioaddr, struct vring_virtqueue *vq, int num_added)
{
   struct vring *vr = &vq->vring;

   wmb();
   vr->avail->idx += num_added;

   mb();
   if (!(vr->used->flags & VRING_USED_F_NO_NOTIFY))
           vp_notify(ioaddr, vq->queue_index);
}
