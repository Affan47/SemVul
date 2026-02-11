target_switch( UniqueInputSwitch      *input_switch,
               UniqueDeviceClassIndex  index,
               UniqueInputChannel     *channel )
{
     UniqueInputEvent    evt;
     UniqueInputTarget  *target;
     UniqueInputChannel *current;

     D_MAGIC_ASSERT( input_switch, UniqueInputSwitch );
     D_ASSERT( index >= 0 );
     D_ASSERT( index < _UDCI_NUM );

     target = &input_switch->targets[index];

     current = target->current;

     D_MAGIC_ASSERT_IF( channel, UniqueInputChannel );
     D_MAGIC_ASSERT_IF( current, UniqueInputChannel );

     if (channel == current)
          return false;

     D_DEBUG_AT( UniQuE_InpSw, "target_switch( index %d, x %d, y %d, channel %p )\n",
                 index, input_switch->x, input_switch->y, channel );

     evt.type = UIET_CHANNEL;

     evt.channel.index = index;
     evt.channel.x     = input_switch->x;
     evt.channel.y     = input_switch->y;

     if (current) {
          evt.channel.selected = false;

          unique_input_channel_dispatch( current, &evt );
     }

     target->current = channel;

     if (channel) {
          evt.channel.selected = true;

          unique_input_channel_dispatch( channel, &evt );
     }

     return true;
}
