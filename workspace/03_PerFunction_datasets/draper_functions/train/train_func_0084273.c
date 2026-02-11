value( const Meta::TrackPtr &track ) const { return track->genre() ? track->genre()->name() : QString(); }
}
