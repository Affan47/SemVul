DequeueRealtimeEvent()
{
    rt_event = rt_queue->DequeueEvent();
    if (rt_event) {
        rt_event_time = rt_event->time;
    }
}
