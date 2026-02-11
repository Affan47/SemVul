SlowAllocate() {
      Chunk* chunk = new Chunk();
      chunk->previous = current_;
      current_ = chunk;

      Node* new_nodes = current_->nodes;
      next_ = new_nodes + 1;
      limit_ = new_nodes + kNodesPerChunk;
      return new_nodes;
    }
