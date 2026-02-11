finishSubPath()
    {

		Vector end = end_;
		Vector start = start_;

		transform_.transform(end);
		transform_.transform(start);

		addPoint(end);

        if(end_ != start_)
            addPoint(start);


        end_ = lastControl_ = start_;
    }
