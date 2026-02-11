status(string mode, float interval, int queue, int running,
                    int completed) {
  stringstream entry;
  entry << "[SCHEDULER] ("<<currentTime<<") Mode: " << mode << " Interval: " << interval
        << " Queue: " << queue << " Running: " << running
        << " Completed: " << completed;
  write(entry.str());
}
